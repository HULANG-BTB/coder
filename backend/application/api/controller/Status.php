<?php
/**
 * FileName: Status.php
 * Product: Lazy OJ
 * Author: Hu Lang
 * DateTime: 2019/9/27 13:07
 * Email: admin@oibit.cn
 * GitHub: https://github.com/HULANG-BTB
 * Description:
 *
 */


namespace app\api\controller;


use app\common\controller\Base;
use app\api\model\Status as StatusModel;
use think\App;
use think\facade\Session;
use think\facade\Validate;

/**
 * Class Status
 * Author: Hu Lang
 * DateTime: 2019/9/27 13:07
 * Email: admin@oibit.cn
 * GitHub: https://github.com/HULANG-BTB
 * @package app\api\controller
 * Description:
 */
class Status extends Base
{
    public function __construct(App $app = null)
    {
        parent::__construct($app);
        $this->Model = new StatusModel();
    }

    public function getStatusList()
    {
        $page = $this->request->post('page/d', 1);
        $limit = $this->request->post('limit/d', 15);
        $id = $this->request->post('id/d', '0');
        $user = $this->request->post('user/s', '');
        $language = $this->request->post('language', '-1');
        $result = $this->request->post('result', '-1');

        $condition = [];
        $id ? $condition['pid'] = $id : null;
        $user ? $condition['uid'] = $user : null;
        is_numeric($language) && $language >= 0 ? $condition['language'] = $language : null;
        is_numeric($result) && $result >= 0 ? $condition['result'] = $result : null;

        $count = $this->Model
            ->where($condition)
            ->count();

        $field = [
            'sid',
            'pid',
            'uid',
            'time',
            'memory',
            'length',
            'result',
            'language',
            'create_time',
            'update_time',
            'judger'
        ];

        $result = $this->Model
            ->where($condition)
            ->page($page, $limit)
            ->field($field)
            ->order('create_time', 'desc')
            ->select();

        $rst = [
            'code' => 1,
            'data' => [
                'page' => $page,
                'limit' => $limit,
                'total' => $count,
                'data' => $result
            ]
        ];
        return json($rst);
    }

    public function insert () {

        $ret = [
            'code' => 0
        ];

        $uid = Session::has('uid') ? Session::get('uid') : false;
        if (!$uid) {
            $ret['msg'] = '登录状态已过期，请重新登录！';
            return json($ret);
        }

        $rule = [
            'pid|题目号' => 'require',
            'language' => 'require',
            'code|源代码' => 'require',
        ];
        $validate = Validate::make($rule);
        if (!$validate->check($this->request->post())) {
            $ret['msg'] = $validate->getError();
            return json($ret);
        }

        $insert = $this->request->post();
        $insert['uid'] = $uid;
        $insert['ip'] = get_client_ipaddress();
        $insert['length'] = strlen($insert['code']);

        $map = [
            'C' => 0,
            'C++' => 1,
            'Pascal' => 2,
            'Java' => 3,
            'Ruby' => 4,
            'Bash' => 5,
            'Python' => 6,
            'PhP' => 7,
            'Perl' => 8,
            'C#'=> 9,
            'Object-c' => 10,
            'FreeBasic' => 11,
            'Scheme' => 12,
            'Clang' => 13,
            'Clang++' => 14,
            'Lua' => 15,
            'JavaScript' => 16,
            'Go' => 17,
            'SQL(sqlite3)' => 18
        ];

        $result = $this->Model->save($insert);
        if ($result) {
            $ret['code'] = 1;
            return json($ret);
        } else {
            $ret['msg'] = '提交失败，稍候重试';
            return json($ret);
        }
    }
}
