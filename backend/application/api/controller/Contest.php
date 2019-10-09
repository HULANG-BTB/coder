<?php

namespace app\api\controller;

use app\common\controller\Base;
use app\api\model\Contest as ContestModel;
use think\App;
use think\Controller;
use think\Request;

class Contest extends Base
{

    public function __construct(App $app = null)
    {
        parent::__construct($app);
        $this->Model = new ContestModel();
    }

    public function getContestList() {
        /**
         * 获取post数据
         */
        $page = $this->request->post('page/d', 1);
        $limit = $this->request->post('limit/d', 15);
        $keyword = $this->request->post('keyword/s', '');

        /**
         * 查询数据
         */
        $result = $this->Model
            ->where($keyword !== '' ? 'title' : 1, $keyword !== '' ? 'like' : '=',  $keyword !== '' ? '%'.$keyword.'%' : 1)
            ->page($page, $limit)
            ->field(['cid', 'uid', 'title', 'start_time', 'end_time', 'private', 'type'])
            ->order(['start_time' => 'desc', 'cid' => 'asc'])
            ->select();

        /**
         * 获取数据总条数
         */
        $count = $this->Model
            ->where($keyword !== '' ? 'title' : 1, $keyword !== '' ? 'like' : '=',  $keyword !== '' ? '%'.$keyword.'%' : 1)
            ->count();

        /**
         * 构造返回结果
         */
        $ret = [
            'code' => 1,
            'data' => [
                'total' => $count,
                'page' => $page,
                'limit' => $limit,
                'data' => $result
            ]
        ];
        return json($ret);
    }

}
